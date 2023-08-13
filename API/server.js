const express = require('express');
const app = express();
const port = 3000;

// Function to map the analog value to the voltage range
function floatMap(x, in_min, in_max, out_min, out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

app.get('/api/voltage', (req, res) => {
  const analogValue = Math.floor(Math.random() * 4096); // Simulating analog value (0 to 4095)
  const voltage = floatMap(analogValue, 0, 4095, 0, 3.3);
  res.json({ analogValue, voltage });
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
