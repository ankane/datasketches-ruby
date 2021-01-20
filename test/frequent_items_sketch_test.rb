require_relative "test_helper"

class FrequentItemsSketchTest < Minitest::Test
  def test_strings
    sketch = DataSketches::FrequentStringsSketch.new(14)
    assert sketch.empty?
  end
end
