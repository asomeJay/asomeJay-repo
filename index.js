const http = require('http');

const port = 3000;

http.createServer(function(request, response) {
    console.log('요청 수신.');
    
    response.writeHead(200, {'Content-Type': 'text/html'});
    response.write('Hello Git!');
    response.end();
    
}).listen(port);

console.log(`서버 시작 - 포트:${port}`);