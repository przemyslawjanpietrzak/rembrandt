const express = require('express');
const path = require('path');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.json());

app.get('/', (req, res) => res.send('Hello World!'))
app.use(express.static(path.join(__dirname, 'public')));

app.listen(3000, () => console.log('Listening on port 3000!'))

app.get('/api/example/1', (req, res) => {
  setTimeout(() => {
    res.send('example string #1');
  }, 3000);
});


app.post('/api/form', (req, res) => {
  setTimeout(() => {
    const { firstName, lastName } = req.body;
    if (firstName === 'John' && lastName === 'Doe') {
      res.send('correct!');
    } else {
      res.send('wrong!');
    }
  }, 3000);
});
