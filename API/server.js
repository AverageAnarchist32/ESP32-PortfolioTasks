const express = require('express');
const bodyParser = require('body-parser'); // Import bodyParser middleware
const app = express();
const port = 3000;

app.use(bodyParser.json()); // Use bodyParser middleware to parse JSON requests

// Function to map the analog value to the voltage range
function floatMap(x, in_min, in_max, out_min, out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Route to receive data from ESP32
app.post('/api/voltage', (req, res) => {
  const { analogValue } = req.body; // Extract analogValue from request body
  const voltage = floatMap(analogValue, 0, 4095, 0, 3.3);
  res.json({ analogValue, voltage });
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
