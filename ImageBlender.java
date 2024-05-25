import ai.djl.Application;
import ai.djl.Model;
import ai.djl.ModelException;
import ai.djl.modality.Classifications;
import ai.djl.modality.cv.Image;
import ai.djl.modality.cv.ImageFactory;
import ai.djl.modality.cv.transform.Resize;
import ai.djl.ndarray.NDArray;
import ai.djl.ndarray.NDManager;
import ai.djl.translate.TranslateException;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class ImageBlender {

    public static void main(String[] args) throws IOException, ModelException, TranslateException {
        String imagePath1 = "path/to/first/image.jpg";
        String imagePath2 = "path/to/second/image.jpg";
        String outputPath = "path/to/output/image.jpg";

        // Load the images
        BufferedImage img1 = ImageIO.read(new File(imagePath1));
        BufferedImage img2 = ImageIO.read(new File(imagePath2));

        // Ensure both images are of the same size
        BufferedImage resizedImg2 = resizeImage(img2, img1.getWidth(), img1.getHeight());

        // Blend the images
        BufferedImage blendedImage = blendImages(img1, resizedImg2);

        // Save the blended image
        ImageIO.write(blendedImage, "jpg", new File(outputPath));
    }

    private static BufferedImage resizeImage(BufferedImage originalImage, int targetWidth, int targetHeight) {
        Image img = ImageFactory.getInstance().fromImage(originalImage);
        img.getTransforms().add(new Resize(targetWidth, targetHeight));
        return (BufferedImage) img.getWrappedImage();
    }

    private static BufferedImage blendImages(BufferedImage img1, BufferedImage img2) {
        int width = img1.getWidth();
        int height = img1.getHeight();
        BufferedImage blendedImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int rgb1 = img1.getRGB(x, y);
                int rgb2 = img2.getRGB(x, y);

                int r1 = (rgb1 >> 16) & 0xff;
                int g1 = (rgb1 >> 8) & 0xff;
                int b1 = rgb1 & 0xff;

                int r2 = (rgb2 >> 16) & 0xff;
                int g2 = (rgb2 >> 8) & 0xff;
                int b2 = rgb2 & 0xff;

                int r = (r1 + r2) / 2;
                int g = (g1 + g2) / 2;
                int b = (b1 + b2) / 2;

                int blendedRGB = (r << 16) | (g << 8) | b;
                blendedImage.setRGB(x, y, blendedRGB);
            }
        }

        return blendedImage;
    }
}
