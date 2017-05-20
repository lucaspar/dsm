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

i.      Criar o processo cliente            (ler .config, estruturas de dados, escolha do servidor e divisão)
ii.     Criar o processo serviço            (ler .config, operações em memória compartilhada (IPC), log)
iii.    Criar comunicação cliente-serviço   (sockets)
iv.     Múltiplas threads                   (habilitar concorrência no processo de serviço)
v.      Criar o processo snapshot           (ler .config, ler memória compartilhada (IPC))
vi.     Snapshot master                     (combina snaps em único arquivo no disco)

_____
DONE:

i.      Cliente         (lê .config, escolhe servidor, data struct, serializa, envia para servidor)
ii.     Servidor        (lê .config, recebe dados, de-serializa, opera sobre memória compartilhada)
iii.    Comunicação     (sockets entre cliente e servidor)
iv.     Concorrência    (nova thread para cada conexão)
v.      Snapshot        -NONE-
vi.     Snapshot master -NONE-

_____
TODO:

i.      Cliente         Dividir mensagens grandes entre servidores, diferenciar pgithubedidos de leitura de escrita.
ii.     Servidor        Atender pedidos de leitura e escrita.     Salvar log de operações em arquivo (opcional)
iii.    Comunicação     -COMPLETED-
iv.     Concorrência    Testar concorrência com ipc implementado
v.      Snapshot        Lê memória compartilhada e envia para master (caso não seja o master)
vi.     Snapshot master Recebe conteúdo dos outros, salva em disco