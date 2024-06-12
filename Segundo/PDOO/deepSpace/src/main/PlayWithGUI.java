/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package main;

import deepspace.*;
import View.*;
import View.GUI.MainWindow;
import controller.Controller;
/**
 *
 * @author carmenc
 */
public class PlayWithGUI {
    public static void main(String[] args) {
        GameUniverse model = new GameUniverse();
        View view = MainWindow.getInstance();
        Controller controller = Controller.getInstance();
        controller.setModelView(model, view);
        controller.start();
    }
}
