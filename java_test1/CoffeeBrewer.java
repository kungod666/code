package java_test1;
// 咖啡机类，继承产品类
public class CoffeeBrewer extends Product {
    private String model;
    private String waterSupply;
    private int numberOfCups;

    public CoffeeBrewer(String code, String description, double price,
                        String model, String waterSupply, int numberOfCups) {
        super(code, description, price);
        this.model = model;
        this.waterSupply = waterSupply;
        this.numberOfCups = numberOfCups;
    }

    public String getModel() { return model; }
    public String getWaterSupply() { return waterSupply; }
    public int getNumberOfCups() { return numberOfCups; }

    // 格式：code_description_price_model_waterSupply_numberOfCups
    public String toString() {
        return super.toString() + "_" + model + "_" + waterSupply + "_" + numberOfCups;
    }
}
