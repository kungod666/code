import java.io.*;

// 主控制台程序
public class GourmetCoffee {
    private Catalog catalog;
    private Order currentOrder;
    private Sales sales;
    private BufferedReader reader;

    public GourmetCoffee() {
        catalog = new Catalog();
        currentOrder = new Order();
        sales = new Sales();
        reader = new BufferedReader(new InputStreamReader(System.in));
        loadCatalog();
        loadSales();  // 加载示例订单数据
    }

    // 硬编码加载产品目录
    private void loadCatalog() {
        catalog.addProduct(new Coffee("C001", "Colombia, Whole, 1 lb", 17.99,
                "Colombia", "Medium", "Rich", "Strong", "Medium", "Full"));
        catalog.addProduct(new Coffee("C002", "Colombia, Ground, 1 lb", 18.75,
                "Colombia", "Medium", "Rich", "Strong", "Medium", "Full"));
        catalog.addProduct(new Coffee("C003", "Italian Roast, Whole, 1 lb", 16.50,
                "Italy", "Dark", "Bold", "Intense", "Low", "Heavy"));
        catalog.addProduct(new Coffee("C004", "Italian Roast, Ground, 1 lb", 16.50,
                "Italy", "Dark", "Bold", "Intense", "Low", "Heavy"));
        catalog.addProduct(new Coffee("C005", "French Roast, Whole, 1 lb", 15.99,
                "France", "Dark", "Smoky", "Pungent", "Low", "Heavy"));
        catalog.addProduct(new CoffeeBrewer("B001", "Home Coffee Brewer", 150.00,
                "BrewMaster 1000", "Automatic", 12));
        catalog.addProduct(new CoffeeBrewer("B002", "Coffee Brewer, 2 Warmers", 200.00,
                "BrewMaster 2000", "Automatic", 24));
        catalog.addProduct(new CoffeeBrewer("B003", "Coffee Brewer, 3 Warmers", 280.00,
                "BrewMaster 3000", "Pour-over", 36));
        catalog.addProduct(new Product("A001", "Almond Flavored Syrup", 9.00));
        catalog.addProduct(new Product("A002", "Irish Creme Flavored Syrup", 11.50));
        catalog.addProduct(new Product("A003", "Mint Flavored Syrup", 10.00));
        catalog.addProduct(new Product("A004", "Caramel Flavored Syrup", 12.00));
        catalog.addProduct(new Product("A005", "Gourmet Coffee Cookies", 7.50));
    }

    // 加载示例销售数据（与实验要求输出匹配）
    private void loadSales() {
        Order order1 = new Order();
        order1.addItem(new OrderItem(catalog.getProduct("C001"), 3));
        order1.addItem(new OrderItem(catalog.getProduct("C002"), 2));
        order1.addItem(new OrderItem(catalog.getProduct("A001"), 3));
        order1.addItem(new OrderItem(catalog.getProduct("A002"), 3));
        sales.addOrder(order1);

        Order order2 = new Order();
        order2.addItem(new OrderItem(catalog.getProduct("C001"), 4));
        order2.addItem(new OrderItem(catalog.getProduct("C003"), 3));
        order2.addItem(new OrderItem(catalog.getProduct("A001"), 4));
        order2.addItem(new OrderItem(catalog.getProduct("A002"), 3));
        order2.addItem(new OrderItem(catalog.getProduct("A003"), 5));
        sales.addOrder(order2);

        Order order3 = new Order();
        order3.addItem(new OrderItem(catalog.getProduct("C005"), 8));
        order3.addItem(new OrderItem(catalog.getProduct("B001"), 2));
        order3.addItem(new OrderItem(catalog.getProduct("B002"), 1));
        order3.addItem(new OrderItem(catalog.getProduct("B003"), 2));
        order3.addItem(new OrderItem(catalog.getProduct("A001"), 3));
        order3.addItem(new OrderItem(catalog.getProduct("A004"), 6));
        sales.addOrder(order3);

        Order order4 = new Order();
        order4.addItem(new OrderItem(catalog.getProduct("C001"), 2));
        order4.addItem(new OrderItem(catalog.getProduct("C002"), 2));
        order4.addItem(new OrderItem(catalog.getProduct("C003"), 2));
        order4.addItem(new OrderItem(catalog.getProduct("A001"), 2));
        sales.addOrder(order4);
    }

    public void displayCatalog() {
        System.out.println("Product Catalog:");
        for (Product p : catalog) {
            System.out.println(p.getCode() + " " + p.getDescription());
        }
    }

    public void displayProductInfo() throws IOException {
        System.out.print("Product code> ");
        String code = reader.readLine();
        Product p = catalog.getProduct(code);
        if (p != null) {
            System.out.println(p.toString());
        } else {
            System.out.println("Product not found.");
        }
    }

    public void displayOrder() {
        if (currentOrder.getNumberOfItems() == 0) {
            System.out.println("Current order is empty.");
        } else {
            System.out.println("Current Order:");
            for (OrderItem item : currentOrder) {
                System.out.println(item.toString());
            }
            System.out.println("Total = " + currentOrder.getTotalCost());
        }
    }

    public void addModifyProduct() throws IOException {
        System.out.print("Product code> ");
        String code = reader.readLine();
        Product p = catalog.getProduct(code);
        if (p == null) {
            System.out.println("Product not found.");
            return;
        }
        System.out.print("Quantity> ");
        int quantity = Integer.parseInt(reader.readLine());
        OrderItem existing = currentOrder.getItem(p);
        if (existing != null) {
            existing.setQuantity(quantity);
            System.out.println("Order item updated.");
        } else {
            currentOrder.addItem(new OrderItem(p, quantity));
            System.out.println("Order item added.");
        }
    }

    public void removeProduct() throws IOException {
        System.out.print("Product code> ");
        String code = reader.readLine();
        Product p = catalog.getProduct(code);
        if (p == null) {
            System.out.println("Product not found.");
            return;
        }
        OrderItem item = currentOrder.getItem(p);
        if (item != null) {
            currentOrder.removeItem(item);
            System.out.println("Order item removed.");
        } else {
            System.out.println("Product not found in current order.");
        }
    }

    public void saleOrder() {
        if (currentOrder.getNumberOfItems() > 0) {
            sales.addOrder(currentOrder);
            currentOrder = new Order();
            System.out.println("Sale registered.");
        } else {
            System.out.println("Current order is empty.");
        }
    }

    public void displayOrdersSold() {
        if (sales.getNumberOfOrders() == 0) {
            System.out.println("No orders have been sold.");
        } else {
            int orderNum = 1;
            for (Order order : sales) {
                System.out.println("--------------------------------");
                System.out.println("Order " + orderNum);
                System.out.println();
                for (OrderItem item : order) {
                    System.out.println(item.toString());
                }
                System.out.println();
                System.out.println("Total = " + order.getTotalCost());
                orderNum++;
            }
        }
    }

    // 显示包含某产品的订单数量
    public void displayNumberOfOrders(Product product) {
        int count = 0;
        for (Order order : sales) {
            if (order.getItem(product) != null) {
                count++;
            }
        }
        System.out.println("Number of orders that contains the product "
                + product.getCode() + ": " + count);
    }

    // 显示每个产品的总销量
    public void displayTotalQuantityOfProducts() {
        for (Product p : catalog) {
            int totalQty = 0;
            for (Order order : sales) {
                OrderItem item = order.getItem(p);
                if (item != null) {
                    totalQty += item.getQuantity();
                }
            }
            System.out.println(p.getCode() + " " + totalQty);
        }
    }

    private int getChoice() throws IOException {
        System.out.println();
        System.out.println("[0] Quit");
        System.out.println("[1] Display catalog");
        System.out.println("[2] Display product");
        System.out.println("[3] Display current order");
        System.out.println("[4] Add|modify product to|in current order");
        System.out.println("[5] Remove product from current order");
        System.out.println("[6] Register sale of current order");
        System.out.println("[7] Display sales");
        System.out.println("[8] Display number of orders with a specific product");
        System.out.println("[9] Display the total quantity sold for each product");
        System.out.print("choice> ");
        return Integer.parseInt(reader.readLine());
    }

    public void run() throws IOException {
        int choice;
        do {
            choice = getChoice();
            switch (choice) {
                case 1: displayCatalog(); break;
                case 2: displayProductInfo(); break;
                case 3: displayOrder(); break;
                case 4: addModifyProduct(); break;
                case 5: removeProduct(); break;
                case 6: saleOrder(); break;
                case 7: displayOrdersSold(); break;
                case 8:
                    System.out.print("Product code> ");
                    String code = reader.readLine();
                    Product p = catalog.getProduct(code);
                    if (p != null) {
                        displayNumberOfOrders(p);
                    } else {
                        System.out.println("Product not found.");
                    }
                    break;
                case 9: displayTotalQuantityOfProducts(); break;
                case 0: System.out.println("Goodbye!"); break;
                default: System.out.println("Invalid choice.");
            }
        } while (choice != 0);
    }

    public static void main(String[] args) throws IOException {
        new GourmetCoffee().run();
    }
}
