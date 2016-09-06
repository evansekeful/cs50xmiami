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
        
        // render form
        render("sell_form.php", ["balance" => $balance, "positions" => $positions, "title" => "Sell"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        
        // look-up and store user's position on individual stock
        $stock = lookup($_POST["symbol"]);
        $shares = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        $sell = $stock["price"] * $shares[0]["shares"];
    
        // delete stock
        CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // update user portfolio
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $sell, $_SESSION["id"]);
        
        // update user history
        CS50::query("INSERT INTO history (user_id, type, time, symbol, shares, total) VALUES (?, ?, NOW(), ?, ?, ?)", $_SESSION["id"], "SELL", $_POST["symbol"], $shares[0]["shares"], $sell);
    }
    
    // redirect to confirmation upon validation
    redirect("/");
?>