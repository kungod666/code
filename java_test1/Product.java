package java_test1;
// 产品类
public class Product {
    private String code;
    private String description;
    private double price;

    public Product(String code, String description, double price) {
        this.code = code;
        this.description = description;
        this.price = price;
    }

    public String getCode() {
        return code;
    }

    public String getDescription() {
        return description;
    }

    public double getPrice() {
        return price;
    }

    // 比较产品代码是否相同
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj instanceof Product) {
            Product other = (Product) obj;
            return code.equals(other.code);
        }
        return false;
    }

    // 格式：code_description_price
    public String toString() {
        return code + "_" + description + "_" + price;
    }
}