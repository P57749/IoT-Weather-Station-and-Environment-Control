function updateSensorData(data) {
    document.getElementById("temperature").textContent = "Temperature: " + data.temperature + " °C";
    document.getElementById("humidity").textContent = "Humidity: " + data.humidity + " %";
    document.getElementById("pressure").textContent = "Pressure: " + data.pressure + " Pa";
    // Update sensor data from the SY300 sensor if available
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
  