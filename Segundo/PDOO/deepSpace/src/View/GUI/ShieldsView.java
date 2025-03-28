/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JPanel.java to edit this template
 */
package View.GUI;

import deepspace.ShieldToUI;

/**
 *
 * @author carmenc
 */
public class ShieldsView extends javax.swing.JPanel implements CombatElementView{

    private boolean selected = false;
    /**
     * Creates new form ShieldsView
     */
    public ShieldsView() {
        initComponents();
        setOpaque(selected);
    }
    
    @Override
    public boolean isSelected(){
        return selected;
    }
    
    //actualiza las variables con los datos
    public void setShieldBooster(ShieldToUI sb){
        nuses.setText(Integer.toString(sb.getUses()));
        nboost.setText(Float.toString(sb.getBoost()));
        revalidate();
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

        shieldbooster = new javax.swing.JLabel();
        uses = new javax.swing.JTextField();
        boost = new javax.swing.JTextField();
        nuses = new javax.swing.JLabel();
        nboost = new javax.swing.JLabel();

        shieldbooster.setText("Shield Booster");

        uses.setText("Uses: ");
        uses.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                usesActionPerformed(evt);
            }
        });

        boost.setText("Boost:");
        boost.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                boostActionPerformed(evt);
            }
        });

        nuses.setText("nuses");

        nboost.setText("nboost");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(uses, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(shieldbooster)
                    .addComponent(boost, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(48, 48, 48)
                        .addComponent(nuses))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(40, 40, 40)
                        .addComponent(nboost)))
                .addContainerGap(42, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(shieldbooster)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(uses, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(nuses))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(boost, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(nboost))
                .addContainerGap(24, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void usesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_usesActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_usesActionPerformed

    private void boostActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_boostActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_boostActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextField boost;
    private javax.swing.JLabel nboost;
    private javax.swing.JLabel nuses;
    private javax.swing.JLabel shieldbooster;
    private javax.swing.JTextField uses;
    // End of variables declaration//GEN-END:variables
}
