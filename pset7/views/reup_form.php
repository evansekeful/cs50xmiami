<div>
    <h2 id="balance"><strong>Current Balance: </strong>$<?= number_format($balance[0]["cash"], 2) ?></h2>
</div>
<div>
    <form action="reup.php" method="post">
    <fieldset>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Ballin'?</button>
        </div>
    </fieldset>
</div>