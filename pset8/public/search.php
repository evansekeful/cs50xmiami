<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // search database for places matching $_GET["geo"], store in $places
    $places = CS50::query("SELECT * FROM places WHERE postal_code LIKE ? OR place_name LIKE ?","%" . $_GET["geo"] . "%", "%" . $_GET["geo"] . "%"); //would work better with combined column place_name, admin_code1

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>