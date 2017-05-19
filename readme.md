# SISTEMAS DISTRIBUÍDOS
 -------------------
## Trabalho 1: Aplicação Cliente-Servidor
### 22/05/17 - avaliação em laboratório
_____________________

#### 1. Requisitos e descrição do sistema

* A comunicação cliente-servidor é feita por sockets (TCP ou UDP);
* O processo servidor deve atender requisições simultaneamente (threads);
* Há múltiplos servidores para ampliar o espaço de endereçamento de um sistema;
* Cada servidor gerencia uma porção de memória local;
* O cliente acessa a memória através de operações de leitura e escrita;
* O serviço deve proteger acessos concorrentes à região crítica;

* Há snapshots periódicos funcionam como um backup de toda a memória compartilhada;
* Os snapshots rodam em um processo diferente do serviço de memória;
* Os snapshots salvam cópias do estado global da memória em disco;
* Há um processo de snapshot em cada máquina que disponibiliza um segmento de memória;
* Um dos processos de snapshot solicita o conteúdo aos demais e escreve um arquivo consolidado;

#### 2. Elementos do projeto

A. Processos serviço (disponibilizam a memória compartilhada aos clientes)
    * Acesso ao arquivo de configuração
    * Acesso à porção de memória local que será compartilhada (k bytes)
    * Implementam sockets para se comunicar com os clientes
    * Abrem uma nova thread a cada comunicação
    * Protegem acessos concorrentes com semáforos (região crítica)
    * Log de escrita e leitura (não é requisito, mas útil ao debugar)

B. Processos snapshot (fazem backups periódicos da memória compartilhada)
    * Acesso ao arquivo de configuração para reconhecer outros servidores
    * Rodam periodicamente
    * Processo diferente ao de serviço de memória
    * Copiam a memória compartilhada (comunicação entre processos)
    * Enviam a memória copiada ao processo principal de snapshot
    * O processo principal de snapshot combina os snaps recebidos e salva em disco

C. Processos cliente (utilizam o serviço de memória compartilhada)
    * Acesso ao arquivo de configuração
    * Capazes de requisitar operações de leitura e escrita na memória compartilhada
    * Gerenciam para quais servidores pedir leitura e escrita com base na posição de memória
    * Gerenciam a divisão da informação em múltiplos servidores caso necessário

D. Arquivo de configuração (configurações do sistema - mcomp.cfg)
    * Será universal (mesmo em todas as máquinas)
    * Contém o tamanho de memória alocado localmente (k)
    * Contém o número de servidores (N)
    * Contém o mapa da rede (ip dos outros servidores)

#### 3. Desenvolvimento

_____
REQS:

i.      Criar o processo cliente (ler .config, estruturas de dados, escolha do servidor e divisão)
ii.     Criar o processo serviço (ler .config, operações em memória compartilhada com semáforos, log)
iii.    Criar comunicação cliente-serviço (sockets, lidar com retorno (falha/sucesso))
iv.     Múltiplas threads (habilitar concorrência no processo de serviço)
v.      Criar o processo snapshot (ler .config, ler memória compartilhada (com. entre processos))
vi.     Combinar snapshots e salvar em disco no processo principal (sockets again)

_____
DONE:

i.      Processo cliente (lê .config, escolhe servidor, envia dados para salvar)
ii.     Processo servidor (lê .config, opera sobre memória compartilhada)
iii.    Comunicação entre servidor e clientes
iv.     Concorrência - servidor cria nova thread para cada conexão
v.      - NONE -
vi.     - NONE -

_____
TODO:

i.      Enviar estrutura de dado sobre a rede, dividir mensagens grandes entre servidores
ii.     Salvar estrutura recebida na memória compartilhada, salvar log de operações em arquivo
iii.    - COMPLETED -
iv.     Testar concorrência, corrigir "stack smashing" when joining the thread vector
v.      Criar processo snapshot, ler memória compartilhada
vi.     Snapshot principal recebe conteúdo dos outros e salva em disco