<?php

    // configuration
    require("../includes/config.php");
    
    if ($_SESSION["id"] == NULL)
    {
        redirect("login.php");
    }
    else
    {
        // lookup and store user's history
        $transactions = CS50::query("SELECT * FROM history WHERE user_id=?", $_SESSION["id"]);
        
        render("history_display.php", ["transactions" => $transactions, "title" => "History"]);
    }
    
?>