<table class="table table-striped">

    <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th><strong>Total</strong></th>
        </tr>
    </thead>

    <tbody>
                <?php foreach ($transactions as $transaction): ?>
        
            <tr>
                <td><?= $transaction["type"] ?></td>
                <td><?= $transaction["time"] ?></td>
                <td><?= $transaction["symbol"] ?></td>
                <td><?= $transaction["shares"] ?></td>
                <td><strong>$<?= number_format($transaction["total"], 2) ?></strong></td>
            </tr>
            
                <?php endforeach ?>
    </tbody>

</table>