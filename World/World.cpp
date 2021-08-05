#include "World.hpp"
#include <iostream>
#include <algorithm>

std::vector<std::shared_ptr<IModel>> World::getModelsInBox(Box box)
{
	std::vector<std::shared_ptr<IModel>> outBuffer;

	for (auto model : *m_models.get())
		if (model->m_position->x >= box.Xmin
				&& model->m_position->x <= box.Xmax
				&& model->m_position->y >= box.Ymin
				&& model->m_position->y <= box.Ymax)
			outBuffer.push_back(model);

	return outBuffer;
}

void World::setModel(std::shared_ptr<IModel> pModel)
{
	if (std::find((*m_models).begin(), (*m_models).end(), pModel) == (*m_models).end())
		m_models->push_back(pModel);
}

std::shared_ptr<IModel> World::getPlayer()
{
	std::shared_ptr<IModel> player;
	for (auto model : *m_models.get())
		if (model->m_control == IModel::CONTROL_PLAYER)
			player = model;

	return player;
}
