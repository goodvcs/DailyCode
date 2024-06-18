import tensorflow as tf


class MyDenseLayer(tf.keras.layers.Layer):
    def __init__(self, input_dim, output_dim):
        super(MyDenseLayer, self).__init__()

        self.W = self.add_weight([input_dim, output_dim])
        self.b = self.add_weight([1, output_dim])

        def call(self, inputs):
            z = tf.matmul(inputs, self.W) + self.b

            output = tf.math.sigmoid(z)
            return output





