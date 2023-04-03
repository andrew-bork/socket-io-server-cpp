const net = require("net");
for(let i = 0;  i < 10; i ++){
const connection = net.connect(3000, "localhost");
    connection.on("connect", () => {
        console.log("connection successful");
        connection.write("Hello World!\n");
    })

    connection.on("data", (data) => {
        console.log(data.toString());
        connection.destroy();
    })
}