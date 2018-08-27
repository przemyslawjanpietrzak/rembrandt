const express = require('express');
const path = require('path');
const app = express()

app.get('/', (req, res) => res.send('Hello World!'))
app.use(express.static(path.join(__dirname, 'public')));

app.listen(3000, () => console.log('Listening on port 3000!'))