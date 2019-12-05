package physicalobject;

public class Planet extends PhysicalObject {

  private final String state; //״̬
  private final String colar; //��ɫ
  private final double planetRadius; //���ǰ뾶
  private final double trackRadius; //����뾶
  private final double speed; //��ת�ٶ�
  private final String orientation; //��ת����
  private final double sitha; //��ʼ�Ƕ�

  // Abstraction function:
  //  represents orbital object in the StellarSystem
  // Representation invariant:
  //    state is the planet's state
  //  colar is the planet's color
  //  planetRadius is the planet's radius
  //  trackRadius is the radius of planet's track
  //  trackRadius > planetRadius
  //    0 <= sitha < 360
  //  speed is the planet's speed
  //  orientation is the planet's orientation
  //  sitha is the planet's sitha
  // Safety from rep exposure:
  //   All fields are private and final

  private void checkRep() {
    assert trackRadius > planetRadius;
    assert sitha >= 0 && sitha <= 360;
  }

  /**Constructor.*/
  public Planet(String name, String state, String colar, 
      double planetRadius, double trackRadius, double speed,
      String orientation, double sitha) {
    super(name);
    this.state = state;
    this.colar = colar;
    this.planetRadius = planetRadius;
    this.trackRadius = trackRadius;
    this.speed = speed;
    this.orientation = orientation;
    this.sitha = sitha;
  }

  /**Get string label of a planet's state.*/
  public String getState() {
    return state;
  }

  /**Get string label of a planet's color.*/
  public String getColar() {
    return colar;
  }

  /**Get double label of a planet's planetRadius.*/
  public double getPlanetRadius() {
    checkRep();
    return planetRadius;
  }

  /**Get double label of a planet's trackRadius.*/
  public double getTrackRadius() {
    checkRep();
    return trackRadius;
  }

  /**Get double label of a planet's speed.*/
  public double getSpeed() {
    return speed;
  }

  /**Get string label of a planet's orientation.*/
  public String getOrientation() {
    return orientation;
  }

  /**Get double label of a planet's sitha.*/
  public double getSitha() {
    checkRep();
    return sitha;
  }
}
