import java.util.ArrayList;
import java.util.Iterator;

// 订单类，包含多个订单条目
public class Order implements Iterable<OrderItem> {
    private ArrayList<OrderItem> items;

    public Order() {
        items = new ArrayList<>();
    }

    public void addItem(OrderItem orderItem) {
        items.add(orderItem);
    }

    public void removeItem(OrderItem orderItem) {
        items.remove(orderItem);
    }

    public Iterator<OrderItem> iterator() {
        return items.iterator();
    }

    // 根据产品找到对应的订单条目
    public OrderItem getItem(Product product) {
        for (OrderItem item : items) {
            if (item.getProduct().equals(product)) {
                return item;
            }
        }
        return null;
    }

    public int getNumberOfItems() {
        return items.size();
    }

    public double getTotalCost() {
        double total = 0.0;
        for (OrderItem item : items) {
            total += item.getValue();
        }
        return total;
    }
}