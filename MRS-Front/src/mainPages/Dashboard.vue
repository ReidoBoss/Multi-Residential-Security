<template>
    <div>
      <input type="text" v-model="messageToSend" placeholder="Type a message...">
      <button @click="sendMessage">Send</button>
      <button @click="closedoor">Close Door</button>
      <button @click="opendoor">Open Door</button>

      <h1>WebSocket Messages:</h1>
      <ul>
        <li v-for="message in messages" :key="message.id">{{ message.content }}</li>
      </ul>
    </div>
  </template>
  
  <script setup>
  import { ref, onMounted } from 'vue';
  import axios from "axios";
  const messages = ref([]);
  const messageToSend = ref('');
  let ws;
  
  function handleIncomingMessage(event) {
    const data = event.data;
    if(data == "Letter A Pressed!"){
      sendEmail("A","SHOPEE DELIVERY","Shopee delivery");
    }
    else if(data == "Letter B Pressed!"){
      sendEmail("B","Maningils Utang","Utang naningil");
    }
    else if(data == "Letter C Pressed!"){
      sendEmail("C","Naabot na ko","Naabot na ko");
    }
    else if(data == "Letter D Pressed!"){
      sendEmail("D","Rybryb ni","Door");
    }
    else if(data== "Max is Reached!"){
      sendEmail("Too many times","Somebody tried to access your door","Robber!");
    }
    messages.value.push({ id: messages.value.length + 1, content: data });
  }
  
  function sendMessage() {
    if (ws && ws.readyState === WebSocket.OPEN) {
      ws.send(messageToSend.value);
      messageToSend.value = ''; 
    }
  }

  function opendoor() {
    if (ws && ws.readyState === WebSocket.OPEN) {
      ws.send("180");
    }
  }
  function closedoor() {
    if (ws && ws.readyState === WebSocket.OPEN) {
      ws.send("1");
    }
  }
  
  onMounted(() => {
    ws = new WebSocket('ws://172.16.30.13/ws');
  
    ws.onopen = () => {
      console.log('Connected to WebSocket server');
    };
  
    ws.onmessage = handleIncomingMessage;
  
    ws.onclose = () => {
      console.log('Disconnected from WebSocket server');
    };
  
    ws.onerror = (error) => {
      console.error('WebSocket error:', error);
    };
  
    return () => {
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.close();
      }
    };
  });


const sendEmail = async (letter,message,subject) => {

  try{
      const formData = new FormData();

      formData.append('email',"marianneleighreyes27@gmail.com");
      formData.append('subject',subject);
      formData.append('letter',letter);
      formData.append('message',message);

      await axios.post("http://localhost:8080/sendMail",formData,{
      headers: {
      "Content-Type" : "multipart/form-data",
          },
      });
  }   
  catch(error){

      alert(error);
  }

}
  </script>
  