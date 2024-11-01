# Ransomware Simples

<div align="center">
  <img src="https://media.giphy.com/media/RiiCMVx8jWEt3EeJnf/giphy.gif" width="100%" alt="Skull gif"/>
</div>
<p align="center"><a href="https://giphy.com/gifs/ilovefriday-aqsa-xenocarr-smokehijabi-RiiCMVx8jWEt3EeJnf"></a></p>

Ransomware Simples é um projeto educacional desenvolvido em C para demonstrar como um ransomware básico pode ser implementado. Este projeto é exclusivamente para fins de aprendizado sobre desenvolvimento de malware e segurança cibernética.

**AVISO:** Este software é um exemplo educacional e não deve ser usado para atividades maliciosas ou ilegais. A utilização deste código em ambientes reais pode levar a consequências legais.

## Criado por WesleyA0101

## Tecnologias Usadas

<div align="center">
  <img src="https://icongr.am/devicon/c-original.svg?size=128&color=currentColor" alt="C Logo" width="60" height="60"/>
  <img src="https://icongr.am/devicon/vim-original.svg?size=128&color=currentColor" alt="Vim Logo" width="60" height="60"/>
</div>

## Tabela de Conteúdos

- [Características](#características)
- [Pré-requisitos](#pré-requisitos)
- [Instalação](#instalação)
- [Uso](#uso)
- [Avisos Importantes](#avisos-importantes)
- [Contribuições Futuras](#contribuições-futuras)

## Características

- **Criptografia de Arquivos:** O ransomware criptografa arquivos no diretório especificado usando SHA-256.
- **Geração de Chave:** Uma chave de criptografia é gerada aleatoriamente para cada execução.
- **Envio de E-mail:** Após a criptografia, um e-mail é enviado para um endereço especificado, informando sobre o resgate.
- **Arquivos de Resgate:** Um arquivo de resgate é criado, informando ao usuário como recuperar seus dados.

## Pré-requisitos

Antes de começar, você precisará ter:

- Um sistema operacional baseado em Linux ou gerar um executável no Windows.
- Compilador `gcc` instalado para compilar o código.
- Bibliotecas `libssl` e `libcurl` instaladas.

## Instalação

Clone o repositório e compile o projeto:

```bash
git clone https://github.com/seuusuario/ransomware_simples.git
cd ransomware_simples
gcc ransomware_simples.c -o ransomware_simples -lssl -lcrypto -lcurl
```

## Uso

```bash
./ransomware_simples
```

## Nota: Execute este programa em um ambiente controlado e apenas para fins de teste.

## Avisos Importantes

- Este ransomware não possui uma função de reversão de criptografia até o momento. Os arquivos criptografados não podem ser recuperados sem uma implementação futura     dessa funcionalidade.

- O uso deste software em sistemas não autorizados é ilegal e pode resultar em consequências legais graves. Este projeto deve ser utilizado somente em ambientes de teste controlados.

## Contribuições Futuras
Este projeto será atualizado com novas funcionalidades e melhorias. Fique atento para atualizações que incluirão:

- Implementação de um método de reversão de criptografia.
- Melhorias na interface e design.
- Expansão da funcionalidade para suportar diferentes métodos de criptografia.
