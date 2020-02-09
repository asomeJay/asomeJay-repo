import app from "./app";

const PORT = 4000;

const handle_listening = () =>
console.log(`Listening on : http://localhost:${PORT}`);

app.listen(PORT, handle_listening);

