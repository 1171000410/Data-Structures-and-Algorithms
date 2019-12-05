package exception;

@SuppressWarnings("serial")
public class MyException extends RuntimeException {
  // ������Ϣ
  private String expMsg = "MyException";

  public MyException(String msg) {
    this.expMsg = msg;
  }

  public String getExpMsg() {
    return this.toString() + expMsg;
  }

}
