function updateRealTimeData(data) {
  document.getElementById("current_time").textContent = data.datetime;
  document.getElementById("light").textContent = "Light: " + data.light + " lx";
  document.getElementById("lightning").textContent = "Lightning Distance: " + data.lightning + " km";
  document.getElementById("wind_direction").textContent = "Wind Direction: " + data.wind_direction + " degrees";
  document.getElementById("wind_speed").textContent = "Wind Speed: " + data.wind_speed + " Hz";
  document.getElementById("rainfall").textContent = "Rainfall: " + (data.rainfall === true ? "Detected" : "Not Detected");
}

function updateOneMinuteData(data) {
  document.getElementById("temperature").textContent = "Temperature: " + data.temperature + " °C";
  document.getElementById("humidity").textContent = "Humidity: " + data.humidity + " %";
  document.getElementById("pressure").textContent = "Pressure: " + data.pressure + " Pa";
  // Add the sensor data for other sensors with 1-minute update interval
}

function fetchRealTimeData() {
  fetch("/").then(response => response.json())
    .then(data => updateRealTimeData(data))
    .catch(error => console.error("Error fetching real-time sensor data: ", error));
}

function fetchOneMinuteData() {
  fetch("/").then(response => response.json())
    .then(data => updateOneMinuteData(data))
    .catch(error => console.error("Error fetching 1-minute sensor data: ", error));
}

function sendControlAction(action) {
  fetch(action).then(response => {
    if (response.ok) {
      console.log("Control action sent successfully.");
      fetchOneMinuteData(); // Fetch updated 1-minute sensor data after control action
    } else {
      console.error("Failed to send control action.");
    }
  }).catch(error => console.error("Error sending control action: ", error));
}

// Fetch real-time sensor data every 5 seconds
setInterval(fetchRealTimeData, 5000);
fetchRealTimeData(); // Fetch real-time sensor data on page load

// Fetch 1-minute update interval data every 60 seconds
setInterval(fetchOneMinuteData, 60000);
fetchOneMinuteData(); // Fetch 1-minute update interval data on page load
