-- RoundedBackground.lua

loadType("algine::Object")
loadType("algine::Widget")
loadType("algine::Painter")
loadType("algine::RectF")
loadType("algine::Dimen")
loadType("algine::Unit")
loadType("algine::Paint")
loadType("algine::Color")

function onDrawBackground(self, painter)
    painter:setPaint(self.background)

    painter:drawRoundRect(
        RectF(0, 0, self.width, self.height),
        Dimen(8, Unit.dp):pixels(self:getParentWindow()))
end
