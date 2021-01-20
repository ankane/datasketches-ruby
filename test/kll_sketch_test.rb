require_relative "test_helper"

class KllSketchTest < Minitest::Test
  def test_ints
    sketch = DataSketches::KllIntsSketch.new(200)
    assert sketch.empty?
    sketch.update(1)
    sketch.update(2)
    sketch.update(3)

    assert_equal 1, sketch.min_value
    assert_equal 3, sketch.max_value
    assert_in_delta 2, sketch.quantile(0.5)
  end

  def test_floats
    sketch = DataSketches::KllFloatsSketch.new(200)
    assert sketch.empty?
    sketch.update(1)
    sketch.update(2)
    sketch.update(3)

    assert_in_delta 1, sketch.min_value
    assert_in_delta 3, sketch.max_value
    assert_in_delta 2, sketch.quantile(0.5)
  end
end
