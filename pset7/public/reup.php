<?php

    // configuration
    require("../includes/config.php");
    
    if ($_SESSION["id"] == NULL)
    {
        redirect("login.php");
    }

    // if user reached page via GET (as by clicking a link or via redirect)
    else if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // user's portfolio
        require("../includes/positions.php");
        
        // else render form
        render("reup_form.php", ["balance" => $balance, "title" => "Ballin'"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // add money to user's account
        CS50::query("UPDATE users SET cash = cash + 5000 WHERE id = ?", $_SESSION["id"]);
    }
    
    // redirect to buy page
    redirect("buy.php");
?>