require_relative "test_helper"

class ThetaSketchTest < Minitest::Test
  def test_update
    sketch = DataSketches::UpdateThetaSketch.new
    assert sketch.empty?
  end
end
