const express = require('express'); // Import the Express.js framework
const bodyParser = require('body-parser'); // Import bodyParser middleware
const app = express(); // Create an instance of the Express application
const port = 1410; // Port number to listen on

app.use(bodyParser.json()); // Use bodyParser middleware to parse JSON requests

// Function to map the analog value to the voltage range
function floatMap(x, in_min, in_max, out_min, out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Route to receive data from ESP32 via POST
app.post('/api/voltage', (req, res) => {
  const { analogValue } = req.body; // Extract analogValue from request body
  const voltage = floatMap(analogValue, 0, 4095, 0, 3.3);
  res.json({ analogValue, voltage }); // Respond with JSON containing analogValue and voltage
});

// Route to handle GET requests for /api/voltage
app.get('/api/voltage', (req, res) => {
  res.send('GET request received'); // Respond with a simple message (modify as needed)
});

// Start the server and listen on the specified port
app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
