<div>
    <h2 id="balance"><strong>Current Balance: </strong>$<?= number_format($balance[0]["cash"], 2) ?></h2>
</div>
<div>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>TOTAL</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($positions as $position): ?>
    
        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["name"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td>$<?= number_format($position["price"], 2) ?></td>
            <td><strong>$<?= number_format($position["total"], 2) ?></strong></td>
        </tr>
        
            <?php endforeach ?>
        </tbody>
    </table>
</div>
