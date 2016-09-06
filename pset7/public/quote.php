<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("quote_form.php", ["title" => "Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup(strtoupper($_POST["symbol"]));

        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol to get a quote.");
        }
        else
        {
            if ($stock === false)
           {
               apologize("You must provide a valid stock symbol to get a quote.");
           }
           else
           {
               render("quote_display.php", ["stock" => $stock]);
           }
        }
        
    }
?>