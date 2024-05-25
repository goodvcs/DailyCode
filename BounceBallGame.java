import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.Timer;

public class BounceBallGame extends JPanel implements ActionListener {
    private Ball ball;
    private Timer timer;

    public BounceBallGame() {
        setPreferredSize(new Dimension(800, 600));
        setBackground(Color.BLACK);

        ball = new Ball(100, 100, 30, 5, 5, Color.RED);

        timer = new Timer(16, this);  // ~60 FPS
        timer.start();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        ball.draw(g);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        ball.update(getBounds());
        repaint();
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Bounce Ball Game");
        BounceBallGame gamePanel = new BounceBallGame();
        frame.add(gamePanel);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}
