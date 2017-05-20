## Distributed Shared Memory
###### Aplicação distribuída cliente-servidor para compartilhamento de memória em rede

---

### 1. Requisitos do sistema

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

### 2. Elementos do projeto

A. Processos serviço (disponibilizam a memória compartilhada aos clientes)
* Acesso ao arquivo de configuração
* Acesso à porção de memória local que será compartilhada (k bytes)
* Implementam sockets para se comunicar com os clientes
* Abrem uma nova thread a cada comunicação
* Protegem acessos concorrentes com semáforos (região crítica)
* Log de escrita e leitura (opcional)

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

_____

### 3. Desenvolvimento

#### Requisitos

| Dominio         | Tarefas                                                             |
| --------------- | ------------------------------------------------------------------- |
| Cliente         | Ler .config, estruturas de dados, escolha do servidor e divisão
| Servidor        | Ler .config, operações em memória compartilhada (IPC), log
| Comunicação     | Servidor <-> cliente, snapshot -> snapshot master
| Concorrência    | Habilitar concorrência no processo servidor
| Snapshot        | Ler .config, ler memória compartilhada (IPC), combinar snaps em único arquivo no disco

#### Done

| Dominio         | Tarefas                                                             |
| --------------- | ------------------------------------------------------------------- |
| Cliente         | Lê .config, divide mensagem, escolhe servidor, monta estrutura de dados, serializa, envia para servidor
| Servidor        | Lê .config, recebe dados, desserializa, salva em memória compartilhada
| Comunicação     | Sockets entre cliente e servidor
| Concorrência    | Abre nova thread para cada conexão
| Snapshot        | Criado processo

#### To do

| Dominio         | Tarefas                                                             |
| --------------- | ------------------------------------------------------------------- |
| Cliente         | Construir pedidos de leitura e escrita.
| Servidor        | Atender pedidos de leitura e escrita. Salvar log de operações em disco (opcional)
| Comunicação     | Comunicação via rede entre processos de snapshot
| Concorrência    | -
| Snapshot        | Lê memória compartilhada, envia para master, (master) recebe snapshots, (master) salva em disco
