const http = require('http');
const port = 3000;
http.createServer((request, response) => {
console.log('Request received.');
response.writeHead(200, {'Content-Type': 'text/html'});
response.write('readme.md');
response.end();
}).listen(port);
console.log(`Server has stared - port:${port}`);
