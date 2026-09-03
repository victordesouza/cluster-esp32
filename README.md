Oii prof, boa noite, pedi pro gemini resumir todas as anotações e nossa conversa em grupo para as decisões de projeto, em relação ao cronograma é só um esboço, nos alinhamos em grupo de acordo com o senhor também.


Resumo Estruturado do Projeto (Cluster de ESP32 - Comunicação Paralela/MPI)

Aqui está a consolidação completa de todo o histórico das suas anotações em aula, diretrizes de implementação, arquitetura técnica e papéis para o gerenciamento do seu grupo de 7 integrantes.

1.⁠ ⁠Objetivo Geral e Escopo
Desenvolver um ambiente de execução paralela em um cluster físico de 5 placas ESP32 (1 Mestre e 4 Trabalhadoras), simulando o comportamento de um sistema MPI (Message Passing Interface) leve sobre FreeRTOS, com paralelismo em dois níveis (entre placas e entre os dois núcleos de cada placa).

2.⁠ ⁠Arquitetura e Mapeamento (Físico vs. Lógico)

    Topologia Física: 5 ESP32 interligadas via switch e cabos de rede.

    Processos Lógicos: Suporte a múltiplos processos virtuais (ex: 15 processos distribuídos nas 5 ESPs).

    Identificação: Cada ESP descobre sua identidade no inicialização lendo seu MAC Address e consultando uma tabela estática.

    Distribuição Sequencial: O mapeamento do processo (ID/Rank) para a ESP é feito de forma determinística por módulo (ex: ID % 4).

    Flash/Deployment: Carregamento do código em cada ESP (com plano futuro/ideal para atualização via OTA/Wi-Fi).

3.⁠ ⁠As 5 Primitivas do Protocolo

    init: Executa no startup, carrega a tabela estática de MACs/IDs e descobre a identidade da ESP.

    myrank: Retorna o ID lógico/rank do processo atual.

    send(destinatario, &dado, tamanho): Não-bloqueante (estilo write/sendsocket). Consulta a tabela de roteamento local e envia via rede sem passar obrigatoriamente pelo Mestre.

    recv(remetente, &dado, tamanho): Bloqueante por padrão. Aguarda a mensagem do processo remetente especificado.

    broadcast: Sequência de envios para múltiplos nós, dividida em Broadcast Send (envia dados) e Broadcast Receive (escuta e recebe).

4.⁠ ⁠Modelo de Execução no FreeRTOS

    Concorrência Local: Cada processo/rank na ESP roda como uma Task do FreeRTOS.

    Paralelismo Duplo:

        Nível 1: Paralelismo distribuído entre as diferentes ESPs físicas.

        Nível 2: Paralelismo local explorando os 2 núcleos (dual-core) de cada ESP32 via tarefas no FreeRTOS.

5.⁠ ⁠Matriz de Atribuição e Gestão do Grupo (7 Integrantes)
Como são 7 participantes e 5 primitivas chave, a divisão de frentes de trabalho para o drive de acompanhamento fica estruturada assim:

    Membro 1 (Primitiva 1): Desenvolvimento do init (Leitura do MAC Address, busca na Tabela Estática e atribuição de ID).

    Membro 2 (Primitiva 2): Desenvolvimento do send (Comunicação 1:1 não-bloqueante via sockets e consulta à tabela de roteamento).

    Membro 3 (Primitiva 3): Desenvolvimento do recv (Lógica bloqueante para recepção e sincronização de mensagens).

    Membro 4 (Primitiva 4): Desenvolvimento do broadcast (Funções de envio/recepção para comunicação 1:N).

    Membro 5 (Primitiva 5): Desenvolvimento do myrank (Mapeamento de Tasks FreeRTOS/núcleos do ESP32 para seus IDs de processo).

    Membro 6 (Infraestrutura & Tabela): Gerenciamento das Tasks no FreeRTOS, alocação de núcleos, tabela estática e suporte ao ambiente de hardware (Switch, Cabos e ESPs).

    Membro 7 (Flash & Testes): Automação do gravação (Flash/OTA), testes de integração de programas paralelos e validação dos 15 processos lógicos.

6.⁠ ⁠Prazos e Cronograma Macro

    Início de Setembro: Chegada do hardware (módulos ESP32, switch e cabos de rede).

    Setembro a Outubro: Desenvolvimento individual dos módulos e primitivas.

    Final de Outubro (Deadline): Integração total do cluster, validação do paralelismo e entrega funcional.