require_relative "test_helper"

class KllSketchTest < Minitest::Test
  def test_ints
    sketch = DataSketches::KllIntsSketch.new(14)
    assert sketch.empty?
  end

  def test_floats
    sketch = DataSketches::KllFloatsSketch.new(14)
    assert sketch.empty?
  end
end
