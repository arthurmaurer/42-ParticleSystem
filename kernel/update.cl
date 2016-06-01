
void kernel		update_particles(global particle * particles)
{
	int		i = get_global_id(0);

	particles[i].position += particles[i].velocity / 5000;
}
