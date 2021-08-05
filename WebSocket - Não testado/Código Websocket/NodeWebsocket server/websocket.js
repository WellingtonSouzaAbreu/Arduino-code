var WebSocketServer = require('websocket').server;
var http = require('http');

//Porta que o server irá escutar
const port = 5000;

//Cria o server
var server = http.createServer();

//Server irá escutar na porta definida em 'port'
server.listen(port, () => {
    //Server está pronto
    console.log(`Server está executando na porta ${port}`);
});

//Cria o WebSocket server
wsServer = new WebSocketServer({
    httpServer: server
});

//Chamado quando um client deseja conectar
wsServer.on('request', (request) => {
    console.log('request')
    //Estado do led: false para desligado e true para ligado
    let state = false;

    //Aceita a conexão do client
    let client = request.accept(null, request.origin);

    // console.log(request)

    const path = request.resourceURL.path

    //Chamado quando o client envia uma mensagem
    client.on('message', (message) => {

        if (message.utf8Data == 'Teste message!') {
            console.log(message.utf8Data);
            client.sendUTF('Eae');
        }

        // client.sendUTF('Não foi mensagem de teste');

        if (path == '/json') {
            if (message.type === 'utf8') {
                console.log(message.utf8Data);

                let req = {}

                try {
                    req = JSON.parse(message.utf8Data)
                    client.sendUTF(JSON.stringify(req));
                } catch (err) {
                    client.sendUTF("JSON inválido");
                }
            }
        }

        if (path == '/teste') {
            client.sendUTF("Testado outra URL");
        }
    });

    //Chamado quando a conexão com o client é fechada
    client.on('close', () => {
        console.log("Conexão fechada");
    });
});