The algorithmic problem T033 - Second Trip Discount Scheme is from the 2003 Hong Kong Informatics Olympiad. The problem is as follows:

> A travel agency offers a second trip discount scheme. If a customer takes two trips with the agency, the price of the second trip is reduced by a fixed amount. Given the prices of the two trips, find the maximum discount that the customer can get.

The solution to this problem is as follows:

> Let $p_1$ and $p_2$ be the prices of the two trips. The maximum discount that the customer can get is $p_2 - k$, where $k$ is the smallest integer such that $p_1 + k \le p_2$.

To see this, let's consider the following cases:

* If $p_1 + k < p_2$, then the customer can get a discount of $p_2 - (p_1 + k) = p_2 - p_1 - k$.
* If $p_1 + k = p_2$, then the customer can get a discount of $p_2 - (p_1 + k) = 0$.
* If $p_1 + k > p_2$, then the customer cannot get any discount.

In the first case, the customer can get a discount of $p_2 - p_1 - k$. This is the maximum discount that the customer can get, because if the customer got a larger discount, then the price of the second trip would be negative.

In the second case, the customer cannot get any discount. This is because the price of the second trip is already the same as the price of the first trip.

In the third case, the customer cannot get any discount. This is because the price of the second trip is more than the price of the first trip.

Therefore, the maximum discount that the customer can get is $p_2 - k$, where $k$ is the smallest integer such that $p_1 + k \le p_2$.

I hope this helps! Let me know if you have any other questions.
