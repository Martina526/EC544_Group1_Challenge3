var SerialPort = require("serialport");
var express = require('express');
var app = require('express')();

var http = require('http').Server(app);

var io = require('socket.io')(http);



var portName = process.argv[2],

portConfig = {

  baudRate: 9600,

  parser: SerialPort.parsers.readline("\n")

};

var sp;

sp = new SerialPort.SerialPort(portName, portConfig);



app.get('/', function(req, res){

  res.sendfile('login.html');

});

app.get('/index',function(req,res){
  res.sendfile('index.html');
});



//app.use('/assets',express.static(__dirname));
app.use('/css',express.static(__dirname));
app.use('/js',express.static(__dirname + '/js'));
app.use('/assets',express.static(__dirname + '/assets'));


io.on('connection', function(socket){

  console.log('a user connected');

  socket.on('disconnect', function(){

  });

  socket.on('chat message1', function(msg){

  	//console.log("Received: ", msg);

    sp.write(msg);

  });

   socket.on('test', function(msg){

    //console.log("Received: ", msg);

    sp.write(msg);

     //socket.emit('chat message2', "world");

  });



});



http.listen(3002, function(){

  console.log('listening on *:3002');

});

sp.on("open", function () {

  console.log('open');

  sp.on('data', function(data) {



    console.log('data received: ' + data);

    io.on('connection', function(socket){



    socket.emit("chat message2", data);

  });

 });

});
