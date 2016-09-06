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
        render("buy_form.php", ["balance" => $balance, "title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup(strtoupper($_POST["symbol"]));
        
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must provide the number of shares you would like to purchase.");
        }
        else if ($stock === false)
        {
            apologize("You must provide a valid stock symbol.");
        }
        else if (preg_match('/^\d+$/', $_POST["shares"]) != 1) // non-negative integer
        {
            apologize("You may only purchase whole stocks through this portal.");
        }
        // lookup user's balance
        $balance = CS50::query("SELECT cash FROM users WHERE id =?", $_SESSION["id"]);
        
        // validate buy
        $buy = $_POST["shares"] * $stock["price"];
        
        if ($buy < $balance)
        {
            // insert stock
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) 
            ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"]);
            
            // update user portfolio
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $buy, $_SESSION["id"]);
            
            // update user history
        // update user history
        CS50::query("INSERT INTO history (user_id, type, time, symbol, shares, total) VALUES (?, ?, NOW(), ?, ?, ?)", $_SESSION["id"], "BUY", $_POST["symbol"], $_POST["shares"], $buy);
            
        }
        else
        {
            apologize("Your account balance is insufficient for this transaction.");
        }
    }
    
    // redirect upon validation
    redirect("/");
?>