const express = require('express');
const http = require('http');
const app = express();
const path = require('path');

const server = http.createServer(app); //cria o servidor socket
const io = require('socket.io')(server);


io.on('connection', socket => {
    console.log('Usuário conectado:[ID]', socket.id); //mostra no servidor quando um usuário se conecta e informa o id dele

    socket.on('sendMessage', data => {
        console.log(`Message received: ${data}`)

        socket.emit('receivedMessage', 'Suas preces foram atendidas') //Envia a mensagem para todos conectados na aplicação
    });
});

server.listen(500, () => { //configuração da porta 
    console.log('Servidor online! porta 500');
});