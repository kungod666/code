import java.util.ArrayList;
import java.util.Iterator;

// 产品目录，可以用foreach遍历
public class Catalog implements Iterable<Product> {
    private ArrayList<Product> products;

    public Catalog() {
        products = new ArrayList<>();
    }

    public void addProduct(Product product) {
        products.add(product);
    }

    public Iterator<Product> iterator() {
        return products.iterator();
    }

    // 根据代码找产品，找不到返回null
    public Product getProduct(String code) {
        for (Product p : products) {
            if (p.getCode().equals(code)) {
                return p;
            }
        }
        return null;
    }

    public int getNumberOfProducts() {
        return products.size();
    }
}
