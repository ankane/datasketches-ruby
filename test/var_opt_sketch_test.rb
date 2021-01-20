require_relative "test_helper"

class VarOptSketchTest < Minitest::Test
  def test_works
    sketch = DataSketches::VarOptSketch.new(14)
    assert_equal 14, sketch.k
    assert_equal 0, sketch.n

    sketch.update(1)
    sketch.update(2.0)
    sketch.update("three")
    assert_equal 3, sketch.n
    assert_equal 3, sketch.num_samples

    # assert_equal [[1, 1.0], [2.0, 1.0], ["three", 1.0]], sketch.samples
  end
end
