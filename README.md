# Controle de Insalubridade: Hardware

## Introdução

Este projeto possui o objetivo principal de verificar e auxiliar no gerenciamento do controle de acesso de colaboradores que atuam em funções operacionais as quais apresentam insalubridade controlada em um período específico.

Buscando atender a necessidade principal de segurança dos colaboradores e de manutenção das ações gerenciais da empresa contratante, foi pensado em um sistema que possa facilitar este processo. Considerando um cenário constituído de quatro bancadas de abatedouro de frango com utilização individual de colaborador. Faz-se necessário a identificação e armazenamento dos dados relativos ao período de permanência do colaborador em cada bancada.

As ferramentas utilizadas para o desenvolvimento do projeto visam baixo custo, logo esta característica define uma etapa inicial de pesquisa de viabilidade financeira e adaptabilidade para o desenvolvimento. Assim sendo, as etapas principais para o desenvolvimento deste projeto constituem levantamento de requisitos, modelagem e implementação do banco de dados, implementação da rede de comunicação, aquisição dos dados através dos módulos RFID e demonstração dos dados através do sistema web.

## Descrição do ambiente: hardware

Para o desenvolvimento do módulo de verificação de presença será utilizado componentes detectores de Rádio Frequência (RFID), possibilitando a detecção do funcionário. Para o processamento dos dados lidos dos módulos RFID será utilizado o microcontrolador ESP. 

## Requisitos: hardware
* Cadastro de diversos funcionários.
* Identificar a presença do funcionário em cada bancada.
* Verificar a localização do funcionário considerando data e hora.
* Verificar entrada em sala específica.
* Informar funcionário que passaram o tempo trabalho.

## Arquivos

gravacao.ino: código responsável pela gravação da ID do Funcionário na TAG através do RFID.
leitura.ino: código responsável pela identificação da TAG do funcionário através do RFID quando o mesmo estiver em atividade.
ReadNUID_NodeMCU.ino: código de teste do funcionamento do RFID.
