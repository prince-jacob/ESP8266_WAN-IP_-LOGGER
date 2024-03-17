<?php
// Database credentials
$servername = "localhost";
$username = "your_username";
$password = "your_password";
$database = "your_database";

// Create connection
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Check if the IP address is sent via POST
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["public_ip"])) {
    // Sanitize the input data
    $public_ip = $conn->real_escape_string($_POST["public_ip"]);

    // Insert the IP address into the database
    $sql = "INSERT INTO ip_addresses (ip_address) VALUES ('$public_ip')";
    
    if ($conn->query($sql) === TRUE) {
        echo "IP address saved successfully.";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
} else {
    echo "Invalid request.";
}

$conn->close();
?>
