package DescentPackage;
//import DescentPackage.*;
import Pkg1.*;

public class HelloWorld
{
  public static void main(String[] args) 
  {
    DescentPackage.PrintString ps = new DescentPackage.PrintString();
    PrintPkg1 pkg1 = new PrintPkg1();
    System.out.println("Hello World");
    ps.msg();
    pkg1.msg();
  }
}
