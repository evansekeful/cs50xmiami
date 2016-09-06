<?php

    // configuration
    require("../includes/config.php");
    
    if ($_SESSION["id"] == NULL)
    {
        redirect("login.php");
    }
    else
    {
        // user's portfolio
        require("../includes/positions.php");
        
        // render portfolio
        render("portfolio.php", ["balance" => $balance, "positions" => $positions, "title" => "Portfolio"]);
    }
?>
