function updateSensorData(data) {
  document.getElementById("temperature").textContent = "Temperature: " + data.temperature + " °C";
  document.getElementById("humidity").textContent = "Humidity: " + data.humidity + " %";
  document.getElementById("pressure").textContent = "Pressure: " + data.pressure + " Pa";
  document.getElementById("light").textContent = "Light: " + data.light + " lx";
  document.getElementById("lightning").textContent = "Lightning Distance: " + data.lightning + " km";
  document.getElementById("wind_direction").textContent = "Wind Direction: " + data.wind_direction + " degrees";
  document.getElementById("wind_speed").textContent = "Wind Speed: " + data.wind_speed + " Hz";
  // Update sensor data for rain detection from the 3144 Hall Sensor if available
}

function fetchSensorData() {
  fetch("/").then(response => response.json())
    .then(data => updateSensorData(data))
    .catch(error => console.error("Error fetching sensor data: ", error));
}

function sendControlAction(action) {
  fetch(action).then(response => {
    if (response.ok) {
      console.log("Control action sent successfully.");
    } else {
      console.error("Failed to send control action.");
    }
  }).catch(error => console.error("Error sending control action: ", error));
}

setInterval(fetchSensorData, 5000); // Fetch sensor data every 5 seconds
fetchSensorData(); // Fetch sensor data on page load
