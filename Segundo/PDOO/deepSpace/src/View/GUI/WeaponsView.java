/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JPanel.java to edit this template
 */
package View.GUI;
import deepspace.WeaponToUI;

/**
 *
 * @author carmenc
 */
public class WeaponsView extends javax.swing.JPanel implements CombatElementView{

    
    private boolean selected = false;
    
    //constructor por defecto
    public WeaponsView() {
        initComponents();
        setOpaque(selected);
    }
    
    //true si el objeto está seleccionado 
    @Override
    public boolean isSelected () {
        return selected;
    }
    
    //para que actualice los campos
    void setWeapon(WeaponToUI weapon){
        weapon_type.setText(weapon.getType().toString());
        npower.setText(Float.toString(weapon.getPower()));
        nuses.setText(Integer.toString(weapon.getUses()));
        repaint();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        weapon_type = new javax.swing.JLabel();
        nuses = new javax.swing.JLabel();
        uses = new javax.swing.JTextField();
        power = new javax.swing.JTextField();
        npower = new javax.swing.JLabel();

        weapon_type.setText("Tipo de Arma");

        nuses.setText("nuses");

        uses.setText("Uses:");
        uses.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                usesActionPerformed(evt);
            }
        });

        power.setText("Power: ");
        power.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                powerActionPerformed(evt);
            }
        });

        npower.setText("npower");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(weapon_type))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(19, 19, 19)
                        .addComponent(uses, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(nuses))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(19, 19, 19)
                        .addComponent(power, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(npower)))
                .addContainerGap(30, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(weapon_type)
                .addGap(26, 26, 26)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(nuses)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(uses, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(power, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(npower))))
                .addContainerGap(17, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void usesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_usesActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_usesActionPerformed

    private void powerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_powerActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_powerActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel npower;
    private javax.swing.JLabel nuses;
    private javax.swing.JTextField power;
    private javax.swing.JTextField uses;
    private javax.swing.JLabel weapon_type;
    // End of variables declaration//GEN-END:variables
}