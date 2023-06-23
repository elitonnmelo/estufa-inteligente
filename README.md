# Estufa Inteligente

Este projeto é uma bolsa acadêmica oferecida pelo IFCE campus Boa Viagem, com o objetivo de desenvolver uma estufa inteligente que possa auxiliar no manejo das plantas e possibilitar a criação de novas espécies exóticas que não seriam viáveis no semiárido do Nordeste devido às condições climáticas.

## Fluxograma e Introdução do Projeto

Aqui está o fluxograma que ilustra o funcionamento do projeto:

![Fluxograma](https://user-images.githubusercontent.com/88889584/202822705-b99b9baf-e63b-42bf-a47c-76b9cef79d03.jpg)

### Protótipo do Projeto

A seguir, são apresentadas imagens do protótipo baseado no projeto (observe que não foi incluída uma placa solar no protótipo devido ao alto custo para o nível de desenvolvimento, então foi usado apenas para simulação do projeto com energia elétrica convencional):

![Protótipo 1](https://user-images.githubusercontent.com/88889584/202822756-77bf2bef-5c2e-456b-be96-03f1aeca0558.jpg)

![Protótipo 2](https://user-images.githubusercontent.com/88889584/202822767-a6d2d368-e3fc-4603-a1d1-0a7ff9f7ba91.jpg)

### Esquema de um dos Sensores

Aqui está o esquema de um dos sensores (sensor medidor de umidade do solo - higrômetro) feito no Fritzing:

![Sensor de Umidade do Solo](https://user-images.githubusercontent.com/88889584/202822780-d648ad03-cbb8-4cf4-b03d-b6dd1345ffdf.jpg)

## Funcionamento do Projeto

O projeto consiste em uma estufa inteligente com Arduino, onde são utilizadas placas solares como fonte de energia. O fluxo de funcionamento é o seguinte:

1. A energia é fornecida pelas placas solares.
2. Os sensores DHT11 e o sensor de umidade do solo fazem as leituras.
3. Com base nas leituras, são tomadas decisões de irrigação, acionamento do exaustor ou acionamento das luzes para aquecimento.
4. As informações coletadas são enviadas para um site, aplicativo ou geradas como dados específicos da estufa.

## Atualizações Futuras

Estamos em constante aprimoramento do projeto e planejamos implementar as seguintes atualizações no futuro:

- Integração de sensores adicionais para monitorar parâmetros como temperatura, umidade do ar, nível de CO2, entre outros.
- Desenvolvimento de um aplicativo móvel para controle remoto da estufa e recebimento de notificações.
- Implementação de um sistema de inteligência artificial para análise de dados e sugestões de otimização do cultivo.
- Integração com assistentes virtuais, permitindo comandos de voz para controle da estufa.
- Expansão da base de dados com informações sobre diferentes espécies de plantas e suas necessidades específicas.

## Licença

Este projeto está lic
